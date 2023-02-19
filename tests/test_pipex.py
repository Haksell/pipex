# TODO test one command
# TODO test redirection
# TODO test heredoc

from dataclasses import dataclass
import subprocess


@dataclass
class Execution:
    returncode: int
    stdout: str
    stderr: str


def quote(s):
    return f"'{s}'"


def execute(command):
    exec = subprocess.run(command, shell=True, capture_output=True)
    return Execution(
        0,  # TODO exec.returncode,
        exec.stdout.decode().strip(),
        "\n".join(
            sorted(
                exec.stderr.decode()
                .strip()
                .replace("pipex:", "shell:")
                .replace("bash:", "shell:")
                .split("\n")
            )
        ),
    )


def compare_no_redirection(argv):
    pipex_command = f"make bonus -s && ./pipex_bonus /dev/stdin {' '.join(map(quote, argv))} /dev/stdout"
    pipes = " | ".join(argv)
    bash_command = f"/usr/bin/bash --posix -c -i '{pipes}'"
    pipex_exec = execute(pipex_command)
    bash_exec = execute(bash_command)
    assert pipex_exec == bash_exec, pipes


def test_absolute_path():
    compare_no_redirection(["/usr/bin/ls", "/usr/bin/rev"])
    compare_no_redirection(["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/rev"])
    compare_no_redirection(["/usr/bin/ls", "/usr/bin/wc", "/usr/bin/rev"])
    compare_no_redirection(["/usr/bin/ls", "/usr/bin/wc", "/usr/bin/rev"])
    compare_no_redirection(["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/tac"])
    compare_no_redirection(
        ["/usr/bin/ls", "/usr/bin/rev", "/usr/bin/tac", "/usr/bin/rev", "/usr/bin/tac"]
    )


def test_relative():
    compare_no_redirection(["./tests/wesh", "rev"])
    compare_no_redirection(["./tests/wesh Bonjour", "rev"])
    compare_no_redirection(["./tests/wesh Bonjour Comment Sa Va ???", "rev"])


def test_in_path():
    compare_no_redirection(["ls", "rev"])
    compare_no_redirection(["ls", "rev", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])
    compare_no_redirection(["ls", "rev", "tac"])
    compare_no_redirection(["ls", "rev", "tac", "rev", "tac"])


def test_args():
    compare_no_redirection(["echo wesh la famille", "wc", "rev"])
    compare_no_redirection(["echo wesh la famille", "tr a z"])


def test_permission_denied():
    compare_no_redirection(["Makefile", "ls"])
    compare_no_redirection(["ls", "Makefile"])


def test_command_not_found():
    compare_no_redirection(["wazaaa", "ls"])
    compare_no_redirection(["ls", "wazaaa"])
    compare_no_redirection(["ls", "lol", "ls"])
    compare_no_redirection(["ls", "lol", "ls", "mdr"])
    compare_no_redirection(["ls", "lol", "ls", "mdr", "ls"])
    compare_no_redirection(
        ["ls", "tac", "rev", "ls", "rev", "rev", "rev", "sl", "ls", "rev"]
    )


def test_enoent():
    compare_no_redirection(["./qwert", "ls"])
    compare_no_redirection(["ls", "./qwert"])


def test_misuse_of_shell_builtin():
    compare_no_redirection(["echo a", "ls -w"])
    compare_no_redirection(["ls -w", "echo a"])
