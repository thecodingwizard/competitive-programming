unit lang;

interface
   procedure excerpt(uni: array of longint);
implementation
   uses graderlib;
   var prev: array [0..1100000] of longint;
   var i:longint;
   procedure excerpt(uni: array of longint);
   begin
      prev[uni[0]] := language(prev[uni[0]]);
   end;
begin
   for i:=0 to 1100000 do prev[i] := 0; 
end.
