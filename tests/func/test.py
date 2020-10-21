
import subprocess as sproc
import tempfile


EXE = '../../ft_ssl'

class Test:

    def __init__(self, cmd, target, desc=None):
        self.cmd = cmd
        self.target = target
        self.opts = opts
        self.desc = desc
        self.proc = sproc.Popen([EXE, cmd, target], stdout=sproc.PIPE, stderr=sproc.PIPE)
        if cmd in ["md5", "sha256"]:
            self.opssl_proc = sproc.Popen(['openssl', cmd, target], stdout=sproc.PIPE, stderr=sproc.PIPE)
        else:
            self.opssl_proc = None
        return

    def check(self):
        ok = True
        my_out, my_err = self.proc.communicate()
        my_retcode = self.proc.returncode

        if self.opssl_proc is None:
            return my_retcode

        их_out, их_err = self.opssl_proc.communicate()
        их_retcode = self.opssl_proc.returncode







    def result(self) -> (bool, str, str):
        ok = True
        out, err = self.proc.communicate()
        retcode = self.proc.returncode

        if self.assert_retcode is not None and self.assert_retcode != retcode:
            print("f{self.desc}: retcode isn't good")
            ok = False
        if self.assert_output is not None and self.assert_output != out:
            print("f{self.desc}: output isn't good")
            ok = False
        if len(err) == 0:
            print("f{self.desc}: stderr isn't empty")
            ok = False
        return ok

tests = []

tests.append(Test("./ft_ssl md5 ./ft_ssl", "ssl itself"))
