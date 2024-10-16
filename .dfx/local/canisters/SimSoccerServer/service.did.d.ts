import type { Principal } from '@dfinity/principal';
import type { ActorMethod } from '@dfinity/agent';
import type { IDL } from '@dfinity/candid';

export type ApiError = { 'StatusCode' : number } |
  { 'Other' : string };
export interface FileContentRecord { 'data' : Array<string>, 'header' : string }
export type FileContentRecordResult = { 'Ok' : FileContentRecord } |
  { 'Err' : ApiError };
export interface FileDownloadInputRecord {
  'offset' : bigint,
  'filename' : string,
  'chunksize' : bigint,
}
export interface FileDownloadRecord {
  'done' : boolean,
  'chunk' : Uint8Array | number[],
  'offset' : bigint,
  'filesize' : bigint,
  'chunksize' : bigint,
}
export type FileDownloadRecordResult = { 'Ok' : FileDownloadRecord } |
  { 'Err' : ApiError };
export interface FileUploadInputRecord {
  'chunk' : Uint8Array | number[],
  'offset' : bigint,
  'filename' : string,
  'chunksize' : bigint,
}
export interface FileUploadRecord { 'filesize' : bigint }
export type FileUploadRecordResult = { 'Ok' : FileUploadRecord } |
  { 'Err' : ApiError };
export type Result = { 'ok' : string } |
  { 'err' : StatusCode };
export type StatusCode = number;
export interface StatusCodeRecord { 'status_code' : number }
export type StatusCodeRecordResult = { 'Ok' : StatusCodeRecord } |
  { 'Err' : ApiError };
export interface _SERVICE {
  'file_download_chunk' : ActorMethod<
    [FileDownloadInputRecord],
    FileDownloadRecordResult
  >,
  'file_upload_chunk' : ActorMethod<
    [FileUploadInputRecord],
    FileUploadRecordResult
  >,
  'health' : ActorMethod<[], StatusCodeRecordResult>,
  'play_match' : ActorMethod<[bigint, bigint], string>,
  'start_match' : ActorMethod<[], string>,
}
export declare const idlFactory: IDL.InterfaceFactory;
export declare const init: (args: { IDL: typeof IDL }) => IDL.Type[];
