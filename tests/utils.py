from dataclasses import dataclass
import os
import subprocess

EXECUTABLES = "tests/executables"
UNWRITABLE = "tests/infiles/unwritable"
OUTFILES = "tests/outfiles"
F1 = f"{OUTFILES}/outfile1"
F2 = f"{OUTFILES}/outfile2"


@dataclass
class Execution:
    returncode: int
    stdout: str
    stderr: str
    outfile: str


def quote(s):
    return f"'{s}'"


def execute(command, outfile):
    ex = subprocess.run(command, shell=True, capture_output=True, timeout=3)
    stderr = "\n".join(
        sorted(
            ex.stderr.decode()
            .strip()
            .replace("pipex:", "shell:")
            .replace("bash:", "shell:")
            .split("\n")
        )
    )
    try:
        assert not outfile.startswith("/dev/")
        outfile = open(outfile).read()
    except:
        outfile = ""
    return Execution(ex.returncode, ex.stdout.decode().strip(), stderr, outfile)


def check(argv, *, infile="/dev/stdin", outfile="/dev/stdout"):
    if not outfile.startswith("/dev/") and not outfile.startswith("tests/infiles/"):
        try:
            os.remove(outfile)
        except:
            pass
    pipex_command = f"./pipex_bonus {infile} {' '.join(map(quote, argv))} {outfile}"
    pipes = " | ".join(a or '""' for a in argv)
    bash_command = f"/usr/bin/bash --posix -c -i '< {infile} {pipes} > {outfile}'"
    pipex_exec = execute(pipex_command, outfile)
    bash_exec = execute(bash_command, outfile)
    if pipex_exec != bash_exec:
        print(pipex_command)
        print(pipex_exec)
        print(bash_command)
        print(bash_exec)
        assert False
