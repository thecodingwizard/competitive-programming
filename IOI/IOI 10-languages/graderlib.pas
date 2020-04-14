unit graderlib;
interface
   function language(L: longint): longint;
implementation
uses gradershare;
   function language(L: longint): longint;
   begin
      if L = lnum then right := right + 1;
      language := lnum;
   end;
begin
end.
