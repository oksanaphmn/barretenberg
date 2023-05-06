// WARNING: FILE CODE GENERATED BY BINDGEN UTILITY. DO NOT EDIT!
/* eslint-disable @typescript-eslint/no-unused-vars */
import { BarretenbergBinder } from '../barretenberg_binder/index.js';
import { BufferDeserializer, NumberDeserializer, VectorDeserializer, BoolDeserializer } from '../serialize/index.js';
import { Fr, Fq, Point, Buffer32, Buffer128, Ptr } from '../types/index.js';

export class BarretenbergApi {
  constructor(public binder: BarretenbergBinder) {}

  async destroy() {
    await this.binder.wasm.destroy();
  }

  pedersenInit(): void {
    const result = this.binder.callWasmExport('pedersen_init', [], []);
    return;
  }

  pedersenCompressFields(left: Fr, right: Fr): Fr {
    const result = this.binder.callWasmExport('pedersen_compress_fields', [left, right], [Fr]);
    return result[0];
  }

  pedersenPlookupCompressFields(left: Fr, right: Fr): Fr {
    const result = this.binder.callWasmExport('pedersen_plookup_compress_fields', [left, right], [Fr]);
    return result[0];
  }

  pedersenCompress(inputsBuffer: Fr[]): Fr {
    const result = this.binder.callWasmExport('pedersen_compress', [inputsBuffer], [Fr]);
    return result[0];
  }

  pedersenPlookupCompress(inputsBuffer: Fr[]): Fr {
    const result = this.binder.callWasmExport('pedersen_plookup_compress', [inputsBuffer], [Fr]);
    return result[0];
  }

  pedersenCompressWithHashIndex(inputsBuffer: Fr[], hashIndex: number): Fr {
    const result = this.binder.callWasmExport('pedersen_compress_with_hash_index', [inputsBuffer, hashIndex], [Fr]);
    return result[0];
  }

  pedersenCommit(inputsBuffer: Fr[]): Fr {
    const result = this.binder.callWasmExport('pedersen_commit', [inputsBuffer], [Fr]);
    return result[0];
  }

  pedersenPlookupCommit(inputsBuffer: Fr[]): Fr {
    const result = this.binder.callWasmExport('pedersen_plookup_commit', [inputsBuffer], [Fr]);
    return result[0];
  }

  pedersenBufferToField(data: Buffer): Fr {
    const result = this.binder.callWasmExport('pedersen_buffer_to_field', [data], [Fr]);
    return result[0];
  }

  pedersenHashInit(): void {
    const result = this.binder.callWasmExport('pedersen_hash_init', [], []);
    return;
  }

  pedersenHashPair(left: Fr, right: Fr): Fr {
    const result = this.binder.callWasmExport('pedersen_hash_pair', [left, right], [Fr]);
    return result[0];
  }

  pedersenHashMultiple(inputsBuffer: Fr[]): Fr {
    const result = this.binder.callWasmExport('pedersen_hash_multiple', [inputsBuffer], [Fr]);
    return result[0];
  }

  pedersenHashMultipleWithHashIndex(inputsBuffer: Fr[], hashIndex: number): Fr {
    const result = this.binder.callWasmExport('pedersen_hash_multiple_with_hash_index', [inputsBuffer, hashIndex], [Fr]);
    return result[0];
  }

  pedersenHashToTree(data: Fr[]): Fr[] {
    const result = this.binder.callWasmExport('pedersen_hash_to_tree', [data], [VectorDeserializer(Fr)]);
    return result[0];
  }

  blake2s(data: Buffer): Buffer32 {
    const result = this.binder.callWasmExport('blake2s', [data], [Buffer32]);
    return result[0];
  }

  blake2sToField(data: Buffer): Fr {
    const result = this.binder.callWasmExport('blake2s_to_field', [data], [Fr]);
    return result[0];
  }

  schnorrComputePublicKey(privateKey: Fr): Point {
    const result = this.binder.callWasmExport('schnorr_compute_public_key', [privateKey], [Point]);
    return result[0];
  }

  schnorrNegatePublicKey(publicKeyBuffer: Point): Point {
    const result = this.binder.callWasmExport('schnorr_negate_public_key', [publicKeyBuffer], [Point]);
    return result[0];
  }

  schnorrConstructSignature(message: Buffer, privateKey: Fr): [Buffer32, Buffer32] {
    const result = this.binder.callWasmExport('schnorr_construct_signature', [message, privateKey], [Buffer32, Buffer32]);
    return result as any;
  }

  schnorrVerifySignature(message: Buffer, pubKey: Point, sigS: Buffer32, sigE: Buffer32): boolean {
    const result = this.binder.callWasmExport('schnorr_verify_signature', [message, pubKey, sigS, sigE], [BoolDeserializer()]);
    return result[0];
  }

  schnorrMultisigCreateMultisigPublicKey(privateKey: Fq): Buffer128 {
    const result = this.binder.callWasmExport('schnorr_multisig_create_multisig_public_key', [privateKey], [Buffer128]);
    return result[0];
  }

  schnorrMultisigValidateAndCombineSignerPubkeys(signerPubkeyBuf: Buffer128[]): [Point, boolean] {
    const result = this.binder.callWasmExport('schnorr_multisig_validate_and_combine_signer_pubkeys', [signerPubkeyBuf], [Point, BoolDeserializer()]);
    return result as any;
  }

  schnorrMultisigConstructSignatureRound1(): [Buffer128, Buffer128] {
    const result = this.binder.callWasmExport('schnorr_multisig_construct_signature_round_1', [], [Buffer128, Buffer128]);
    return result as any;
  }

  schnorrMultisigConstructSignatureRound2(message: Buffer, privateKey: Fq, signerRoundOnePrivateBuf: Buffer128, signerPubkeysBuf: Buffer128[], roundOnePublicBuf: Buffer128[]): [Fq, boolean] {
    const result = this.binder.callWasmExport('schnorr_multisig_construct_signature_round_2', [message, privateKey, signerRoundOnePrivateBuf, signerPubkeysBuf, roundOnePublicBuf], [Fq, BoolDeserializer()]);
    return result as any;
  }

  schnorrMultisigCombineSignatures(message: Buffer, signerPubkeysBuf: Buffer128[], roundOneBuf: Buffer128[], roundTwoBuf: Fr[]): [Buffer32, Buffer32, boolean] {
    const result = this.binder.callWasmExport('schnorr_multisig_combine_signatures', [message, signerPubkeysBuf, roundOneBuf, roundTwoBuf], [Buffer32, Buffer32, BoolDeserializer()]);
    return result as any;
  }

  envTestThreads(threads: number, iterations: number): number {
    const result = this.binder.callWasmExport('env_test_threads', [threads, iterations], [NumberDeserializer()]);
    return result[0];
  }

  async envSetData(keyBuf: string, buffer: Buffer): Promise<void> {
    const result = await this.binder.asyncCallWasmExport('env_set_data', [keyBuf, buffer], []);
    return;
  }

  async envGetData(keyBuf: string): Promise<Buffer> {
    const result = await this.binder.asyncCallWasmExport('env_get_data', [keyBuf], [BufferDeserializer()]);
    return result[0];
  }

  eccNewPippenger(points: Buffer, numPoints: number): Ptr {
    const result = this.binder.callWasmExport('ecc_new_pippenger', [points, numPoints], [Ptr]);
    return result[0];
  }

  eccDeletePippenger(pippenger: Ptr): void {
    const result = this.binder.callWasmExport('ecc_delete_pippenger', [pippenger], []);
    return;
  }

  eccPippengerUnsafe(pippengerPtr: Ptr, scalarsPtr: Ptr, from: number, range: number): Point {
    const result = this.binder.callWasmExport('ecc_pippenger_unsafe', [pippengerPtr, scalarsPtr, from, range], [Point]);
    return result[0];
  }

  eccG1Sum(pointsPtr: Ptr, numPoints: number): Point {
    const result = this.binder.callWasmExport('ecc_g1_sum', [pointsPtr, numPoints], [Point]);
    return result[0];
  }

  plonkProverProcessQueue(prover: Ptr): void {
    const result = this.binder.callWasmExport('plonk_prover_process_queue', [prover], []);
    return;
  }

  plonkProverGetCircuitSize(prover: Ptr): number {
    const result = this.binder.callWasmExport('plonk_prover_get_circuit_size', [prover], [NumberDeserializer()]);
    return result[0];
  }

  plonkProverExportProof(prover: Ptr): Buffer {
    const result = this.binder.callWasmExport('plonk_prover_export_proof', [prover], [BufferDeserializer()]);
    return result[0];
  }

  examplesSimpleCreateAndVerifyProof(pippenger: Ptr, g2x: Buffer): boolean {
    const result = this.binder.callWasmExport('examples_simple_create_and_verify_proof', [pippenger, g2x], [BoolDeserializer()]);
    return result[0];
  }
}