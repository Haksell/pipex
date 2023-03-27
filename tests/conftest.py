import os
from utils import EXECUTABLES, OUTFILES, UNWRITABLE
import sys


def pytest_sessionstart(session):
    assert os.system("make -s bonus") == 0
    sys.path.append(os.path.join(os.getcwd(), EXECUTABLES))
    os.chmod(UNWRITABLE, 0o444)
    try:
        os.mkdir(OUTFILES)
    except FileExistsError:
        pass
