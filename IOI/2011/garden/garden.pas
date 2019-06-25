unit garden;

interface

uses gardenlib;

procedure count_routes(N : LongInt;
	 	      M : LongInt;
		      P : LongInt;
		      var R : RArray;
  		      Q : LongInt;
		      var G : array of Longint);

implementation

procedure count_routes(N : LongInt;
		      M : LongInt;
		      P : LongInt;
		      var R : RArray;
  		      Q : LongInt;
		      var G : array of Longint);
var i :Longint;
begin
  for i:=0 to Q-1 do
  begin
    answer(N);
    WriteLn(N);
  end;
end;

end.
