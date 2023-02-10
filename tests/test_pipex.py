import subprocess


def quote(s):
    return f"'{s}'"


def equal_exec(pipex_exec, bash_exec):
    return (
        pipex_exec.returncode == bash_exec.returncode
        and pipex_exec.stdout == bash_exec.stdout
        and pipex_exec.stderr == bash_exec.stderr
    )


def format_error(pipex_exec, bash_exec):
    return "\n".join(
        [
            ":(",
            f"pipex_args={pipex_exec.args}",
            f"bash_args={bash_exec.args}",
            f"pipex_stdout={pipex_exec.stdout}",
            f"bash_stdout={bash_exec.stdout}",
            f"pipex_stderr={pipex_exec.stderr}",
            f"bash_stderr={bash_exec.stderr}",
            f"pipex_return={pipex_exec.returncode}",
            f"bash_return={bash_exec.returncode}",
        ]
    )


def compare_no_redirection(argv):
    pipex_command = f"make bonus -s && ./pipex_bonus {' '.join(map(quote, argv))}"
    bash_command = f"/usr/bin/bash --posix -c -i '{' | '.join(argv)}'"
    pipex_exec = subprocess.run(pipex_command, shell=True, capture_output=True)
    bash_exec = subprocess.run(bash_command, shell=True, capture_output=True)
    assert equal_exec(pipex_exec, bash_exec), format_error(pipex_exec, bash_exec)


def compare_mandatory(argv):
    assert True  # TODO


def compare_bonus(argv):
    assert True  # TODO


# TODO test one command


def test_basic():
    compare_no_redirection(["ls", "rev"])
    compare_no_redirection(["ls", "rev", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])
    compare_no_redirection(["ls", "wc", "rev"])


def test_args():
    compare_no_redirection(["echo wesh la famille", "wc", "rev"])
    compare_no_redirection(["echo wesh la famille", "tr a z"])
