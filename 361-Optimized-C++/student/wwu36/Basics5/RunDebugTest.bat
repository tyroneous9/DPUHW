cd .\Debug

Echo ---A--- > foo.txt
A.exe >> foo.txt
Echo.  >> foo.txt

Echo ---B--- >> foo.txt
B.exe >> foo.txt
Echo.  >> foo.txt

Echo ---C--- >> foo.txt
C.exe >> foo.txt
Echo.  >> foo.txt

Echo ---D--- >> foo.txt
D.exe >> foo.txt
Echo.  >> foo.txt

Echo ---E--- >> foo.txt
E.exe >> foo.txt
Echo.  >> foo.txt

Echo ---F--- >> foo.txt
F.exe >> foo.txt
Echo.  >> foo.txt

Echo ---G--- >> foo.txt
G.exe >> foo.txt
Echo.  >> foo.txt

Echo ---H--- >> foo.txt
H.exe >> foo.txt
Echo.  >> foo.txt

Echo ---I--- >> foo.txt
I.exe >> foo.txt
Echo.  >> foo.txt

Echo ---J--- >> foo.txt
J.exe >> foo.txt
Echo.  >> foo.txt

echo|set /p=testPass: > Output.txt
find /C "Passed: 1" < foo.txt >> Output.txt
Echo.  >> Output.txt

type foo.txt >> Output.txt

copy .\Output.txt .\..\





