unit friend;

interface
function findSample(n: Longint; confidence: array of Longint; host: array of Longint; protocol: array of Longint): Longint;


implementation
function findSample(n: Longint; confidence: array of Longint; host: array of Longint; protocol: array of Longint): Longint;
var
	ans : longint;
begin
	ans := 10;
	findSample := ans;
end;
end.
