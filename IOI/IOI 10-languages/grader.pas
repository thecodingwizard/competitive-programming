program grader;
   uses gradershare, lang;
   var i,n: longint;
   var x,y: char;
   var lan1: array [0..55] of char;
   var lan2: array [0..55] of char;
begin
   n := 0;
   nl := 0;
   right := 0;
   tot := 0;
   while not eof do begin
      read(x,y);
      for i:=0 to 99 do read(uni[i]);
      readln;
      i := 0;
      while (i < nl) and ((lan1[i] <> x) or (lan2[i]<> y)) do i := i + 1;
      if i = nl then begin
         lan1[i] := x; lan2[i] := y; nl := nl + 1;
      end;
      lnum := i;
      excerpt(uni);
      tot := tot + 1;
   end;
   writeln('OK ',100*right/tot:0:2,'%');
end.
