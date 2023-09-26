import streamlit as st
import pandas as pd
from io import StringIO
from annotated_text import annotated_text, parameters

parameters.SHOW_LABEL_SEPARATOR = False

st.set_page_config(layout="wide")
col1, col2 = st.columns(2)

# Remove Header and Footer
hide_st_style = """
<style>
#MainMenu {visibility: hidden;}
footer {visibility: hidden;}
header {visibility: hidden;}
</style>
"""
st.markdown(hide_st_style, unsafe_allow_html=True)



def reset_state():
#  for key in st.session_state.keys():
#    del st.session_state[key]
  st.session_state.log_list = []
  st.session_state.extract_value = ""
  st.session_state.matching_lines = []

# Parse input File and print logs
with col1:
  st.header("Input File")
  uploaded_file = st.file_uploader("Choose a file", on_change=reset_state)
  if uploaded_file is not None:
    #df = pd.read_fwf(uploaded_file)
    #st.table(df)
    for line in uploaded_file.readlines():
      st.session_state.log_list.append(line)
 
    for line in st.session_state.log_list:
      st.code(line) 
  

# Search for the lines which match the value
# Set list of annotated text to matching_lines in session_state
def search_val():
  st.session_state.matching_lines = []
  #st.text (str(st.session_state.keys()))
  if "log_list" in st.session_state:
    val = st.session_state.extract_value 
    for line in st.session_state.log_list:
      split_line = line.decode("ascii").split()
      if val in split_line:
        # TODO  splitting on space. Handle case when val is a substring
        split_line = [x+" " for x in split_line]
        split_line = [(x,"selected") if x == val+" " else x for x in split_line ] 
        st.session_state.matching_lines.append(split_line)

# Take a value, search it in logs and 
# generate pattern
with col2:
  st.header("Template Generation")
  st.session_state.extract_value = st.text_input('Sample value to be extracted')
  st.write('Value to be searched is:', st.session_state.extract_value)
  
  search_val()
  if len(st.session_state.matching_lines) != 0: 
    for line in st.session_state.matching_lines:
      print (line)
      annotated_text(line)  

#  if df.empty == False:
#     for _,line in df.iterrows():
#      print (line)
  
# Show result and allow codgen
#with col3:
#  st.header("Parser Generation")
#  st.image("https://static.streamlit.io/examples/owl.jpg")
