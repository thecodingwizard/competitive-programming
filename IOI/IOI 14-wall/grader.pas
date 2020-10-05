program main;

uses wall;

var 
   n    : longint;
   k    : longint;
   op	       : array of longint;
   left        : array of longint;
   right       : array of longint;
   height      : array of longint;
   finalHeight : array of longint;
   i, j	       : longint;
begin
   read(n);
   read(k);

   setLength(op, k);
   setLength(left, k);
   setLength(right, k);
   setLength(height, k);
   setLength(finalHeight, n);

   for i := 0 to k - 1 do
   begin
      read(op[i]);
      read(left[i]);
      read(right[i]);
      read(height[i]);
   end;

   for j := 0 to n - 1 do
      finalHeight[j] := 0;

   buildWall(n, k, op, left, right, height, finalHeight);

   for j := 0 to n - 1 do
      writeln(finalHeight[j]);
end.
