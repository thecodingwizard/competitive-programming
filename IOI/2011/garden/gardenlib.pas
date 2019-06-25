unit gardenlib;

interface

const
  MAX_M = 1000000;
  
type
  RArray = array [0..MAX_M, 0..1] of LongInt;

procedure answer(x : Longint);

implementation

uses gardenshare;

procedure answer(x : Longint);
begin
  if answer_count >= 2000 then
  begin
    WriteLn('Incorrect.  Too many answers');
    Halt(0);
  end;
  answers[answer_count] := x;
  answer_count := answer_count + 1;
end;

end.
