import logging
from logdecorator import log_on_start, log_on_end, log_on_error
from logdecorator.decorator import log_exception


@log_on_start(logging.CRITICAL, "Enter: {name:s}")
@log_on_start(logging.CRITICAL, "Exit: {name:s}")
@log_on_error (logging.CRITICAL, "Exception !! {e!r}", on_exceptions=(AssertionError), reraise=False)
def my_func(name):
    print (name)
    assert False, "What!!"

my_func("ankur")