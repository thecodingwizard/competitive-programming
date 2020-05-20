program grader;
  uses coprobber;

  var
    N: Integer;
    A: Matrix;
    CopCanWin: Boolean;
    RobberStrategy: array [0..MAX_N-1, 0..MAX_N] of Integer;
    VisitedPositions: Matrix;
    
    c, r, t, copCorner, robberCorner, nextCopCorner: Integer;
  
begin
  Read(N);
  for c := 0 to N-1 do
    for r := 0 to N-1 do
    begin
      Read(t);
      A[c, r] := t = 1;
    end;
  Read(t);
  CopCanWin := t = 1;
  if CopCanWin then
    for c := 0 to N-1 do
      for r := 0 to N do
        Read(RobberStrategy[c, r]);
  for c := 0 to N-1 do
    for r := 0 to N-1 do
      VisitedPositions[c, r] := False;
  
  copCorner := Start(N, A);
  
  if (copCorner <> -1) and not CopCanWin then
  begin
    WriteLn('FAIL');
    WriteLn('Cop cannot catch the robber, but start() did not return -1');
    Halt;
  end;
  
  if (copCorner = -1) and CopCanWin then
  begin
    WriteLn('FAIL');
    WriteLn('Cop can catch the robber, but start() returned -1');
    Halt;
  end;
  
  if not CopCanWin then
  begin
    WriteLn('OK');
    Halt;
  end;
  
  if (copCorner < 0) or (copCorner >= N) then
  begin
    WriteLn('FAIL');
    WriteLn('start() returned a value that is outside the 0..N-1 range');
    Halt;
  end;
  
  robberCorner := RobberStrategy[copCorner, N];
  
  if robberCorner = copCorner then
  begin
    WriteLn('OK');
    Halt;
  end;
  
  while True do
  begin
    nextCopCorner := NextMove(robberCorner);
    
    if (nextCopCorner < 0) or (nextCopCorner >= N)
      or not ((copCorner = nextCopCorner) or A[copCorner, nextCopCorner]) then
    begin
      WriteLn('PARTFAIL');
      WriteLn('nextMove() returned a value that is either outside 0..N-1 ' +
              'or the new cop position is not a neighbour to the previous one');
      Halt;
    end;
    
    copCorner := nextCopCorner;
    
    if VisitedPositions[copCorner, robberCorner] then
    begin
      WriteLn('PARTFAIL');
      WriteLn('the situation repeated');
      Halt;
    end;
    
    VisitedPositions[copCorner, robberCorner] := True;
    
    if copCorner = robberCorner then
    begin
      WriteLn('OK');
      Halt;
    end;
    
    robberCorner := RobberStrategy[copCorner, robberCorner];
    
    if copCorner = robberCorner then
    begin
      WriteLn('OK');
      Halt;
    end;
  end;
end.
