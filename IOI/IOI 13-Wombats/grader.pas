program grader;

uses wombats;

procedure fail(s: string);
begin
    writeln(stderr, s);
    halt(1);
end;

var
    R, C, E, P, Q, W, V1, V2, event, i, j: longint;
    H, V: array[0..4999, 0..199] of LongInt;
    f: text;

begin
    assign(f, 'wombats.in');
    {$I-} reset(f); {$I+}
    if IOResult <> 0 then
        fail('Failed to open input file.');

    readln(f, R, C);
    for i := 0 to R-1 do
        for j := 0 to C-2 do
            read(f, H[i, j]);
    for i := 0 to R-2 do
        for j := 0 to C-1 do
            read(f, V[i, j]);

    init(R, C, H, V);

    read(f, E);
    for i := 1 to E do begin
        read(f, event);
        if event = 1 then begin
            read(f, P, Q, W);
            changeH(P, Q, W);
        end else if event = 2 then begin
            read(f, P, Q, W);
            changeV(P, Q, W);
        end else if event = 3 then begin
            read(f, V1, V2);
            writeln(escape(V1, V2));
        end else
            fail('Invalid event type.')
    end;

    close(f);
end.
