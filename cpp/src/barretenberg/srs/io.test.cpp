#include "barretenberg/ecc/curves/bn254/fq12.hpp"
#include "barretenberg/ecc/curves/bn254/pairing.hpp"
#include "io.hpp"
#include "barretenberg/common/mem.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include "msgpack.hpp"
#include "msgpack-impl.hpp"
#include <cxxabi.h>

using namespace barretenberg;

TEST(io, read_transcript_loads_well_formed_srs)
{
    size_t degree = 100000;
    g1::affine_element* monomials = (g1::affine_element*)(aligned_alloc(32, sizeof(g1::affine_element) * (degree + 2)));
    g2::affine_element g2_x;
    io::read_transcript(monomials, g2_x, degree, "../srs_db/ignition");

    EXPECT_EQ(g1::affine_one, monomials[0]);

    g1::affine_element P[2];
    g2::affine_element Q[2];
    P[0] = monomials[1];
    P[1] = g1::affine_one;
    P[0].y.self_neg();
    Q[0] = g2::affine_one;
    Q[1] = g2_x;
    fq12 res = pairing::reduced_ate_pairing_batch(P, Q, 2);

    EXPECT_EQ(res, fq12::one());
    for (size_t i = 0; i < degree; ++i) {
        EXPECT_EQ(monomials[i].on_curve(), true);
    }
    aligned_free(monomials);
}

struct MyExampleFlat {
    int a;
    std::string b;

    auto serialize_flat(auto ar) { return ar(a, b); }
};

struct MyExampleMap {
    int a;
    std::string b;
    MyExampleFlat flat;

    auto serialize(auto ar) { return ar(NVP(a), NVP(b), NVP(flat)); }
};

template <typename T> struct MsgPackSchema;

struct DefineMapSchema {
    auto operator()() { return std::make_tuple(); }
    auto operator()(auto& key, const auto& value)
    {
        (void)value; // unused except for type
        // TODO terrible memory leak hack
        // since we are serializing proxy objects, these need to exist after this function runs
        // but we will only print schemas once then end the program, so hack is livable
        return std::make_tuple(std::ref(key), std::ref(*new MsgPackSchema<std::decay_t<decltype(value)>>()));
    }

    auto operator()(auto& key, const auto& value, auto&... args)
    {
        (void)value; // unused except for type
        // TODO terrible memory leak hack
        // since we are serializing proxy objects, these need to exist after this function runs
        // but we will only print schemas once then end the program, so hack is livable
        return std::tuple_cat(
            std::make_tuple(std::ref(key), std::ref(*new MsgPackSchema<std::decay_t<decltype(value)>>())),
            (*this)(args...));
    }
};

template <typename T> const char* schema_name()
{
    const char* result = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL);
    std::string result_str = result;
    if (result_str.find("basic_string") != std::string::npos) {
        return "string";
    }
    if (result_str == "i") {
        return "int";
    }
    return result;
}

// TODO in hindsight should have been written against just the msgpack_pack api
template <typename T> struct MsgPackSchema {
    const char* type_name_string = "__typename";
    const char* type_name = schema_name<T>();
    void msgpack_pack(auto& packer) const
        requires msgpack::adaptor::Serializable<T>
    {
        msgpack::adaptor::DefineMapArchive ar;
        T object;
        auto map_definition = object.serialize(ar);
        auto archive_wrapper = [&](auto&... args) { return ar(type_name_string, type_name, args...); };
        auto create_map_schema = [&](auto&... args) {
            DefineMapSchema schema;
            return std::apply(archive_wrapper, schema(args...));
        };
        std::apply(create_map_schema, map_definition.a).msgpack_pack(packer);
    }
    void msgpack_pack(auto& packer) const
        requires msgpack::adaptor::FlatSerializable<T>
    {
        msgpack::adaptor::DefineArchive ar;
        T object;
        auto map_definition = object.serialize_flat(ar);
        auto archive_wrapper = [&](auto&... args) { return ar(type_name_string, type_name, args...); };
        auto create_map_schema = [&](auto&... args) {
            DefineMapSchema schema;
            return std::apply(archive_wrapper, schema(args...));
        };
        std::apply(create_map_schema, map_definition.a).msgpack_pack(packer);
    }
    void msgpack_pack(auto& packer) const
        requires(!msgpack::adaptor::Serializable<T> && !msgpack::adaptor::FlatSerializable<T>)
    {
        packer.pack_str((uint32_t)strlen(type_name));
        packer.pack_str_body(type_name, (uint32_t)strlen(type_name));
    }
};

void pretty_print(const auto& obj)
{
    std::stringstream output;
    msgpack::pack(output, obj);
    std::string output_str = output.str();
    msgpack::object_handle oh = msgpack::unpack(output_str.data(), output_str.size());
    std::cout << "HEY" << std::endl;
    std::cout << oh.get() << std::endl;
}

TEST(io, myexample)
{

    { // pack, unpack
        MyExampleMap my{ 1, "2", { 3, "4" } };
        MsgPackSchema<MyExampleMap> my_schema;
        pretty_print(my);
        pretty_print(my_schema);
        //        std::stringstream ss;
        //        msgpack::pack(ss, my);
        //
        //        std::string const& str = ss.str();
        //        // Write the packed data to a file
        //        std::ofstream ofs("output.msgpack", std::ios::binary);
        //        if (ofs) {
        //            ofs.write(str.data(), (std::streamsize)str.size());
        //            ofs.close();
        //            std::cout << "Binary string written to output.msgpack" << std::endl;
        //        } else {
        //            std::cerr << "Error: Unable to open output.msgpack" << std::endl;
        //        }
        //        msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
        //        msgpack::object obj = oh.get();
        //        std::cout << obj << std::endl;
        //        assert(obj.as<MyExampleMap>() == my);
    }
}