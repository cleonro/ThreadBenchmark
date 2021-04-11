import sys
import os
import local_test
import handlers

path: str = ""


def local_lambda_handler(sqs: dict):
    global path
    context = None
    handler = handlers.LambdaHandler()
    handler.run(sqs, context)


def main(argv):
    global path
    path = os.getenv('LOCAL_TEST_DIRECTORY')
    if path is None:
        print("LOCAL_TEST_DIRECTORY is not specified\n")
        return
    path = path.replace("$HOME", os.getenv('HOME'))
    print("Path: ", path)

    local_watcher = local_test.LocalWatcher(path, local_lambda_handler)
    local_watcher.run()


if __name__ == "__main__":
    main(sys.argv)
