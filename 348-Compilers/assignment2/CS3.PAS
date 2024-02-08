{----------------------------------------------------------------------------

The function COMB2 here uses the stack to compute the function non-recursively.

 Rather than drag to sum-to-date around in a separate variable, it is placed

 on the top of the stack and taken off repeatedly.

 ----------------------------------------------------------------------------}


PROGRAM  combine;

CONST lo_mem = 1;

      hi_mem = 1000;

TYPE  stack = ARRAY [lo_mem..hi_mem] OF INTEGER;

VAR   x,y,stack_pointer : INTEGER;


PROCEDURE  push (number : INTEGER;  VAR s : stack);

    BEGIN
    stack_pointer    := SUCC(stack_pointer);
    s[stack_pointer] := number
    END;


FUNCTION   pop	(VAR s : stack) : INTEGER;

    BEGIN
    pop 	     := s[stack_pointer];
    s[stack_pointer] := 0;
    stack_pointer    := PRED(stack_pointer)
    END;


FUNCTION  isempty  (s : stack) : BOOLEAN;

    BEGIN
    isempty := (stack_pointer = 0)
    END;


PROCEDURE  makeempty  (VAR s : stack);

    VAR  pointer : INTEGER;

    BEGIN

    FOR  pointer := lo_mem  TO	hi_mem	DO
	s[pointer] := 0;

    stack_pointer := 0
    END;


FUNCTION   comb1  (n,m : INTEGER) : INTEGER;

    VAR    s   : stack;

	   sum : INTEGER;

    BEGIN
    makeempty(s);
    push(n,s);
    push(m,s);
    sum := 0;

	REPEAT
	m := pop(s);
	n := pop(s);
	push(sum,s);

	IF  (n = 1)  OR  (m = 0)  OR  (m = n)  THEN
	    BEGIN
	    sum := pop(s);
	    push(sum+1,s)
	    END
	  ELSE
	    BEGIN
	    sum := pop(s);
	    push(n-1,s);
	    push(m-1,s);
	    push(n-1,s);
	    push(m,s);
	    push(sum,s)
	    END;

	sum := pop(s)
	UNTIL  isempty(s);

    comb1 := sum
    END;


FUNCTION   comb2  (n,m : INTEGER) : INTEGER;

    BEGIN

    IF	(n = 1)  OR  (m = 0)  OR  (m = n)  THEN
	comb2 := 1
      ELSE
	comb2 := comb2(n-1,m) + comb2(n-1,m-1)

    END;


BEGIN

    REPEAT
    WRITE('n=');
    READ(x);
    WRITE('   m=');
    READ(y);

    IF	(x <> 0)  AND  (y <> 0)  THEN
	WRITELN('        ',comb2(x,y),'   ',comb1(x,y))

    UNTIL  (x = 0)  AND  (y = 0)

END.