unit wombats;

interface

type
    wombatsArrayType = array[0..4999, 0..199] of LongInt;

procedure init(R, C : LongInt; var H, V : wombatsArrayType);
procedure changeH(P, Q, W: LongInt);
procedure changeV(P, Q, W: LongInt);
function escape(V1, V2 : LongInt) : LongInt;

implementation

procedure init(R, C : LongInt; var H, V : wombatsArrayType);
begin
    { ... }
end;

procedure changeH(P, Q, W: LongInt);
begin
    { ... }
end;

procedure changeV(P, Q, W: LongInt);
begin
    { ... }
end;

function escape(V1, V2 : LongInt) : LongInt;
begin
    escape := 42;
end;

end.
