export const idlFactory = ({ IDL }) => {
  const FileDownloadInputRecord = IDL.Record({
    'offset' : IDL.Nat64,
    'filename' : IDL.Text,
    'chunksize' : IDL.Nat64,
  });
  const FileDownloadRecord = IDL.Record({
    'done' : IDL.Bool,
    'chunk' : IDL.Vec(IDL.Nat8),
    'offset' : IDL.Nat64,
    'filesize' : IDL.Nat64,
    'chunksize' : IDL.Nat64,
  });
  const ApiError = IDL.Variant({
    'StatusCode' : IDL.Nat16,
    'Other' : IDL.Text,
  });
  const FileDownloadRecordResult = IDL.Variant({
    'Ok' : FileDownloadRecord,
    'Err' : ApiError,
  });
  const FileUploadInputRecord = IDL.Record({
    'chunk' : IDL.Vec(IDL.Nat8),
    'offset' : IDL.Nat64,
    'filename' : IDL.Text,
    'chunksize' : IDL.Nat64,
  });
  const FileUploadRecord = IDL.Record({ 'filesize' : IDL.Nat64 });
  const FileUploadRecordResult = IDL.Variant({
    'Ok' : FileUploadRecord,
    'Err' : ApiError,
  });
  const StatusCodeRecord = IDL.Record({ 'status_code' : IDL.Nat16 });
  const StatusCodeRecordResult = IDL.Variant({
    'Ok' : StatusCodeRecord,
    'Err' : ApiError,
  });
  return IDL.Service({
    'file_download_chunk' : IDL.Func(
        [FileDownloadInputRecord],
        [FileDownloadRecordResult],
        ['query'],
      ),
    'file_upload_chunk' : IDL.Func(
        [FileUploadInputRecord],
        [FileUploadRecordResult],
        [],
      ),
    'health' : IDL.Func([], [StatusCodeRecordResult], ['query']),
    'play_match' : IDL.Func([IDL.Nat64, IDL.Nat64], [IDL.Text], []),
    'start_match' : IDL.Func([], [IDL.Text], []),
  });
};
export const init = ({ IDL }) => { return []; };
