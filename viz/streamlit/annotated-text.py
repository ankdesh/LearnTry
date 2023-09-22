import streamlit as st
from annotated_text import annotated_text

strval = st.text_input("Input Text")
strlist = strval.split()

#strval = strval.replace("Ankur", '("Ankur", "verb")')
strlist = [(x,"Great") if x == "Ankur" else x for x in strlist ]

asd = ["This ",
    ("is", "verb"),
    " some ",
    ("annotated", "adj"),
    ("text", "noun"),
    " for those of ",
    ("you", "pronoun"),
    " who ",
    ("like", "verb"),
    " this sort of ",
    ("thing", "noun"),
    "."]

strval = ("Ankur","Deshwal")
asd = [strval]

annotated_text(strlist)
