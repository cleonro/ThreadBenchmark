from system import System


class LambdaHandler:
    def __init__(self):
        self.system = System()

    def process_request(self, record):
        try:
            args = record.split()
            if len(args) < 2:
                return
            out = self.system.execute_external_command('ThreadBenchmark', args)
            print(out, end='')
        except Exception as e:
            print("Unknown exception trying to process record " + str(record) + ": " + str(e))

    def run(self, event, context):
        try:
            for record in event["Records"]:
                self.process_request(record)
        except Exception as e:
            print("Unknown exception while handling event " + str(event) + ", context " + str(context) + ", error " + str(e))
