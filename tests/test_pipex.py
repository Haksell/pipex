import subprocess
from utils import F1, F2, UNWRITABLE, check


def test_norminette():
    assert (
        subprocess.run(
            ["norminette", "includes", "libft", "srcs"], capture_output=True
        ).returncode
        == 0
    )


def test_absolute_path():
    check(["/usr/bin/ls", "/usr/bin/rev"])
    check(["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/rev"])
    check(["/usr/bin/ls", "/usr/bin/wc", "/usr/bin/rev"])
    check(["/usr/bin/ls", "/usr/bin/wc", "/usr/bin/rev"])
    check(["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/tac"])
    check(
        ["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/tac", "/usr/bin/rev", "/usr/bin/tac"]
    )


def test_relative():
    check(["./tests/shout", "rev"])
    check(["./tests/shout Bonjour", "rev"])
    check(["./tests/shout Bonjour Comment Sa Va ???", "rev"])
    check(["./tests/jexistepas", "rev"])


def test_in_path():
    check(["ls", "grep s"])
    check(["ls", "rev"])
    check(["shout mdr", "rev"])
    check(["ls", "rev", "rev"])
    check(["ls", "wc", "rev"])
    check(["ls", "wc", "rev"])
    check(["ls", "rev", "tac"])
    check(["ls", "rev", "tac", "rev", "tac"])


def test_args():
    check(["echo wesh la famille", "wc", "rev"])
    check(["echo wesh la famille", "tr a z"])


def test_fail_execution():
    check(["ls", "/usr/bin/jexistepas"])
    check(["ls", "/bin/ls/fsafsa"])
    check(["ls", "jexistepas"])
    check(["ls", "./Makefile"])
    check(["ls", "/bin/ls/dfs"])
    check(["ls", "/bin"])
    check(["ls", "includes"])
    check(["ls", "./includes"])
    check(["ls", ".."])
    check(["ls", ""])


def test_random_bullshit():
    check(["abc", "def", "ghi", "jkl", "mno", "qrs", "tuv"])
    check(["ls", "rev", "tac", "rev", "tac"])
    check(["echo lol", "echo mdr"], outfile="/dev/full")
    check(["env", "env"], outfile="/dev/full")


def test_permission_denied():
    check(["Makefile", "ls"])
    check(["ls", "Makefile"])
    check(["/dev/null", "rev"])
    check(["ls", "/dev/null"])


def test_command_is_directory():
    check(["..", "rev"])
    check(["ls", ".."])
    check(["../..", "rev"])
    check(["ls", "../.."])
    check(["bin", "rev"])
    check(["ls", "bin"])


def test_command_not_found():
    check(["wazaaa", "ls"])
    check(["ls", "wazaaa"])
    check(["ls", "lol", "ls"])
    check(["ls", "lol", "ls", "mdr"])
    check(["ls", "lol", "ls", "mdr", "ls"])
    check(["ls", "tac", "rev", "ls", "rev", "rev", "rev", "sl", "ls", "rev"])


def test_enoent():
    check(["./qwert", "ls"])
    check(["ls", "./qwert"])


def test_misuse_of_shell_builtin():
    check(["echo a", "ls -w"])
    check(["ls -w", "echo a"])


def test_pipe():
    check(["ls -la", "wc", "wc"])
    check(["eclo lol", "echo lol"])
    check(["echo lol", "eclo lol"])
    check(["echo yo", "less"])
    check(["ls", "echo yes", "grep s"])
    check(["cat", "cat", "ls"])
    check(["cat", "cat", "echo abc"])
    check(["echo bonsoir", "pwd", "asdf", "cat -e"])


def test_yes():
    check(["yes", "wc-l"])
    check(["yes", "ls"])
    check(["yes", "ls", "wc-l"])
    check(["yes", "ls", "wc -l"])
    check(["yes", "head -n 10"])


def test_redirections():
    check(["cat", "rev"], infile="Makefile")
    check(["tac", "rev"], infile="Makefile")
    check(["cat", "rev"], infile="Makefile", outfile=F1)
    check(["tac", "rev"], infile="Makefile", outfile=F2)
    check(["tac", "rev"], infile="Makefile", outfile=UNWRITABLE)
    check(["tac", "rev"], infile=UNWRITABLE, outfile=F1)
    check(["echo lol", "echo mdr"], infile=UNWRITABLE, outfile=UNWRITABLE)
    check(["echo lol", "echo mdr"], infile=UNWRITABLE, outfile=F1)
    check(["echo lol", "echo mdr"], infile=F1, outfile=UNWRITABLE)
    check(["echo lol", "echo mdr"], infile=F1, outfile=F2)
    check(["echo lol", "echo mdr"], infile="qwerty", outfile=F1)
    check(["rev", "tac"], infile="libft")
    check(["rev", "tac"], infile="Makefile", outfile="libft")
