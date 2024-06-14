export const idlFactory = ({ IDL }) => {
  return IDL.Service({ 'train' : IDL.Func([], [IDL.Text], ['query']) });
};
export const init = ({ IDL }) => { return []; };
