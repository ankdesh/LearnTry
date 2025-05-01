import streamlit as st
import subprocess
import time
import threading
import io

def run_subprocess(script_path, output_buffer):
    process = subprocess.Popen(["python", script_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    for line in process.stdout:
        output_buffer.write(line)
    stderr_output = process.stderr.read()
    if stderr_output:
        print(f"Error from subprocess: {stderr_output}")  # Log errors for debugging
    process.wait()


def main():
    st.title("Agentic System Demo")

    user_input = st.chat_input("Ask a question:")
    if user_input:
        st.write(f"You asked: {user_input}")

        # Use a dummy script for now
        script_path = "dummy_script.py"

        # Create an in-memory buffer to capture the subprocess output
        output_buffer = io.StringIO()

        # Start the subprocess in a separate thread
        process_thread = threading.Thread(target=run_subprocess, args=(script_path, output_buffer))
        process_thread.daemon = True  # Allow the main thread to exit even if the subprocess is running
        process_thread.start()

        # Display the rolling text in Streamlit
        output_text = ""
        placeholder = st.empty()
        while process_thread.is_alive():  # Keep updating while the subprocess is running
            time.sleep(1)  # Check for new output every second
            new_output = output_buffer.getvalue()
            if new_output != output_text:
                output_text = new_output
                #placeholder.text(output_text)
                placeholder.markdown(output_text, unsafe_allow_html=True)
                st.write ("\n\n")

        # Final update after the subprocess finishes (if there's any remaining output)
        new_output = output_buffer.getvalue()
        if new_output != output_text:
            output_text = new_output
            placeholder.text(output_text)

        st.write("Process finished.")


if __name__ == "__main__":
    main()
