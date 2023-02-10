# TODO test one command
# TODO test return value
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
        -1,  # TODO exec.returncode
        exec.stdout.decode(),
        exec.stderr.decode().replace("pipex:", "shell:").replace("bash:", "shell:"),
    )


def format_error(pipex_command, bash_command, pipex_exec, bash_exec):
    error = [":(", f"pipex_command={pipex_command}", f"bash_command={bash_command}"]
    if pipex_exec.returncode != bash_exec.returncode:
        error.extend(
            [
                f"pipex_return={pipex_exec.returncode}",
                f"bash_return={bash_exec.returncode}",
            ]
        )
    if pipex_exec.stdout != bash_exec.stdout:
        error.extend(
            [f"pipex_stdout={pipex_exec.stdout}", f"bash_stdout={bash_exec.stdout}"]
        )
    if pipex_exec.stderr != bash_exec.stderr:
        error.extend(
            [f"pipex_stderr={pipex_exec.stderr}", f"bash_stderr={bash_exec.stderr}"]
        )
    return "\n".join(error)


def compare_no_redirection(argv):
    pipex_command = f"make bonus -s && ./pipex_bonus {' '.join(map(quote, argv))}"
    bash_command = f"/usr/bin/bash --posix -c -i '{' | '.join(argv)}'"
    pipex_exec = execute(pipex_command)
    bash_exec = execute(bash_command)
    assert pipex_exec == bash_exec, format_error(
        pipex_command, bash_command, pipex_exec, bash_exec
    )


def compare_mandatory(argv):
    assert True  # TODO


def compare_bonus(argv):
    assert True  # TODO


def test_basic():
    compare_no_redirection(["ls", "rev"])
    compare_no_redirection(["ls", "rev", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])


def test_args():
    compare_no_redirection(["echo wesh la famille", "wc", "rev"])
    compare_no_redirection(["echo wesh la famille", "tr a z"])


def test_permission_denied():
    compare_no_redirection(["Makefile", "ls"])
    compare_no_redirection(["ls", "Makefile"])


def test_command_not_found():
    compare_no_redirection(["wazaaa", "ls"])
    compare_no_redirection(["ls", "wazaaa"])


def test_command_not_found():
    compare_no_redirection(["wazaaa", "ls"])
    compare_no_redirection(["ls", "wazaaa"])


def test_enoent():
    compare_no_redirection(["./qwert", "ls"])
    compare_no_redirection(["ls", "./qwert"])
