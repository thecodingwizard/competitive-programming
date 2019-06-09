program sunyuangrader;
uses friend;

(* Variables *)
var
	n, i: longint;
	confidence, host, protocol: array of longint;
	answer: longint;

(* Main *)
begin
	(* Number of people *)
	read(n);

	(* Dynamic array *)
	setlength(confidence,n);
	setlength(host,n);
	setlength(protocol,n);

	(* Confidence *)
	for i := 0 to n-1 do
		read(confidence[i]);
	
	(* Host and Protocol *)
	for i := 1 to n-1 do
		read(host[i], protocol[i]);
	
	(* Find out answer *)
	answer := findSample(n,confidence,host,protocol);
	writeln(answer);
end.
