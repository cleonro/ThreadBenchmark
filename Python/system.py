import subprocess
import os


class System:
    def __init__(self):
        local_bin_path = os.environ.get("LOCAL_BIN_PATH")
        local_lib_path = os.environ.get("LOCAL_LIB_PATH")
        self.BIN_PATH = "/tmp" if local_bin_path is None else local_bin_path
        self.LIB_PATH = "/tmp" if local_lib_path is None else local_lib_path

    def execute_external_command(self, command, arguments):
        result = self.execute_external_command_and_get_response(command, arguments, False)
        return result

    def execute_external_command_and_get_response(self, command, arguments, system_command):
        try:
            run_env = os.environ.copy()
            if not system_command:
                # set the LD_LIBRARY_PATH environment variable
                run_env['LD_LIBRARY_PATH'] = self.LIB_PATH

                # make the command absolute path (presume all commands are run from the bin folder)
                command = self.BIN_PATH + "/" + command

            call_params = [command]
            for arg in arguments:
                call_params.append(arg)

            f_dev_null = open(os.devnull, 'w')
            process = subprocess.Popen(call_params, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=f_dev_null, env=run_env)
            outs, errs = process.communicate()
            f_dev_null.close()

            if process.returncode != 0:
                print("Failed to execute command: " + command + ", with args: " + str(arguments) + ", error: " + str(errs) + ", out: " + str(outs))
                return None
            return outs.decode()

        except subprocess.CalledProcessError as cpe:
            print("Exception while executing command: " + command + ", with args: " + str(arguments) + ", error: " + str(cpe))
            return None
        except Exception as e:
            print("Exception while executing command: " + command + ", with args: " + str(arguments) + ", error: " + str(e))
            return None
