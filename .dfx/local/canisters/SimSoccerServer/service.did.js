export const idlFactory = ({ IDL }) => {
  return IDL.Service({
    'play_match' : IDL.Func([IDL.Nat64, IDL.Nat64], [IDL.Text], []),
    'start_match' : IDL.Func([], [IDL.Text], []),
  });
};
export const init = ({ IDL }) => { return []; };
