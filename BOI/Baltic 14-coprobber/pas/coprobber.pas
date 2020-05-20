unit coprobber;

interface
  const MAX_N = 500;

  type Matrix = array [0..MAX_N - 1, 0..MAX_N - 1] of Boolean;

  function Start(N: Integer; var A: Matrix): Integer;
  function NextMove(R: Integer): Integer;

implementation

  function Start(N: Integer; var A: Matrix): Integer;
  begin
    Start := 0;
  end;
  
  function NextMove(R: Integer): Integer;
  begin
    NextMove := 0;
  end;

end.
