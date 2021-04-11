from watchdog.events import RegexMatchingEventHandler
from watchdog.events import FileModifiedEvent
from watchdog.observers import Observer


class LocalEventFactory:
    def __init__(self):
        pass

    @staticmethod
    def create_sqs_message_from_file(file_path: str) -> dict:
        sqs_message = {
            "Records": []
        }

        message_file = open(file_path, "r")
        first_line = True
        start_line = "THREAD_BENCHMARK_TEST_FILE\n"
        for line in message_file:
            if first_line:
                if line != start_line:
                    return sqs_message
                first_line = False
                continue
            if line.startswith("#"):
                continue
            sqs_message["Records"].append(line)

        return sqs_message


class LocalWatcher:
    class Handler(RegexMatchingEventHandler):
        def __init__(self, source_path, slot):
            self.slot = slot
            self.source_path = source_path
            if self.source_path[-1] != "/":
                self.source_path += "/"
            self.event_factory = LocalEventFactory()

            super().__init__(ignore_directories=True)

        def __factory(self, event: FileModifiedEvent) -> dict:
            sqs_message = self.event_factory.create_sqs_message_from_file(event.src_path)
            return sqs_message

        # def on_created(self, event):
        #     print("FileSystemEventHandler::on_created -> ", str(event))

        def on_modified(self, event: FileModifiedEvent):
            selected_event = self.__factory(event)
            self.slot(selected_event)

    def __init__(self, source_path, slot):
        self.source_path = source_path
        self.slot = slot
        self.handler = LocalWatcher.Handler(self.source_path, self.slot)
        self.observer = Observer()

    def run(self):
        import time
        self.observer.schedule(self.handler, self.source_path, recursive=True)
        self.observer.start()
        try:
            while True:
                time.sleep(0.1)
        except KeyboardInterrupt:
            self.stop()

    def stop(self):
        self.observer.stop()
        self.observer.join()
