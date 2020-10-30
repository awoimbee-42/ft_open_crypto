
import subprocess as sproc
import tempfile
from os import path

EXE = f"{path.dirname(__file__)}/../../ft_ssl"
FILE = f"{path.dirname(__file__)}/file"

class Test:

    def __init__(self, cmd, output, desc=None):
        self.cmd = cmd
        self.output = bytes(output, "utf-8")
        self.desc = desc
        self.proc = sproc.Popen(cmd, shell=True, stdout=sproc.PIPE, stderr=sproc.PIPE)
        return

    def check(self):
        out, err = self.proc.communicate()
        retcode = self.proc.returncode
        if self.output == out:
            print(f"Test OK: {self.desc}")
        else:
            print(f"Test failed: {self.desc} -> {self.cmd}")
            print(f"\t* stdout: {out}")
            print(f"\t* sterr: {err}")
            print(f"\t* Reference output: {self.output}")

tests = []

tests.append(Test(
    f"echo \"pickle rick\" | {EXE} md5",
    "c5e433c1dbd7ba01e3763a9483e74b04\n",
    "basic stdin"
))

tests.append(Test(
    f"echo \"Do not pity the dead, Harry.\" | {EXE} md5 -p",
    "Do not pity the dead, Harry.\n2d95365bc44bf0a298e09a3ab7b34d2f\n",
    "stdin -p"
))

tests.append(Test(
    f"echo \"Pity the living.\" | {EXE} md5 -q -r",
    "e20c3b973f63482a778f3fd1869b7f25\n",
    "stdin -q -r"
))

tests.append(Test(
    f"{EXE} md5 {FILE}",
    f"MD5 ({FILE}) = 53d53ea94217b259c11a5a2d104ec58a\n",
    "file"
))

tests.append(Test(
    f"{EXE} md5 -r {FILE}",
    f"53d53ea94217b259c11a5a2d104ec58a {FILE}\n",
    "file -r"
))

tests.append(Test(
    f"{EXE} md5 -s \"pity those that aren't following baerista on spotify.\"",
    f"MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f\n",
    "-s long"
))

tests.append(Test(
    f"echo \"be sure to handle edge cases carefully\" | {EXE} md5 -p {FILE}",
    f"be sure to handle edge cases carefully\n3553dc7dc5963b583c056d1b9fa3349c\nMD5 ({FILE}) = 53d53ea94217b259c11a5a2d104ec58a\n",
    "First edge case (stdin -p + file)"
))

tests.append(Test(
    f"echo \"some of this will not make sense at first\" | {EXE} md5 {FILE}",
    f"MD5 ({FILE}) = 53d53ea94217b259c11a5a2d104ec58a\n",
    "Don't read stdin in file passed"
))

tests.append(Test(
    f"echo \"but eventually you will understand\" | {EXE} md5 -p -r {FILE}",
    f"but eventually you will understand\ndcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a {FILE}\n",
    "Read stdin (-p) and file"
))

tests.append(Test(
    f"echo \"GL HF let's go\" | {EXE} md5 -p -s \"foo\" {FILE}",
    f"GL HF let's go\nd1e3cc342b6da09480b27ec57ff243e2\nMD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 ({FILE}) = 53d53ea94217b259c11a5a2d104ec58a\n",
    "Read stdin (-p), str (-s) and file"
))

tests.append(Test(
    f"echo \"one more thing\" | {EXE} md5 -r -p -s \"foo\" {FILE} -s \"bar\"",
    f"one more thing\na0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 \"foo\"\n53d53ea94217b259c11a5a2d104ec58a {FILE}\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory\n",
    "File mode and error handling"
))

tests.append(Test(
    f"echo \"just to be extra clear\" | {EXE} md5 -r -q -p -s \"foo\" {FILE}",
    f"just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a\n",
    "final test"
))

for t in tests:
    t.check()
