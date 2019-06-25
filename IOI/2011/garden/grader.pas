program grader;

uses gardenlib, garden, gardenshare;

const
  MAX_Q = 2000;
  
var
  N,M,P : LongInt;
  Q : LongInt;
  G : array [0..MAX_Q] of Longint;
  R : RArray;
  solutions : array [0..MAX_Q] of LongInt;

procedure ReadInput;
var ii,a,b : LongInt;
begin
  ReadLn(N,M,P);
  for ii:=0 to M-1 do
    ReadLn(R[ii][0],R[ii][1]);
  ReadLn(Q);
  for ii:=0 to Q-1 do
    Read(G[ii]);
  ReadLn;
  for ii:=0 to Q-1 do
    Read(solutions[ii]);
end;

var
  correct : Boolean;
  i : Integer;
begin
  ReadInput;
  answer_count := 0;
  count_routes(N,M,P,R,Q,G);

  if answer_count > Q then
  begin
    WriteLn('Incorrect.  Too many answers.');
    Halt(0);
  end;

  if answer_count < Q then
  begin
    WriteLn('Incorrect.  Too few answers.');
    Halt(0);
  end;
  
  correct := true;
  for i:=0 to Q-1 do
    if answers[i]<>solutions[i] then
      correct := false;
  if correct then
    WriteLn('Correct.')
  else
  begin
    WriteLn('Incorrect.');
    Write('Expected : ');
    for i:=0 to Q-1 do
      Write(solutions[i],' ');
    WriteLn;
    Write('Returned : ');
    for i:=0 to Q-1 do
      Write(answers[i],' ');
    WriteLn;
  end;
end.
