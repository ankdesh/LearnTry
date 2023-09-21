import streamlit as st
import pandas as pd
import numpy as np
from transformers import pipeline

st.title('Sentiment Analysis')

@st.cache_data
def load_pipeline():
    pipe = pipeline("sentiment-analysis")
    return pipe

pipe = load_pipeline()

inp = st.text_input('Input Text', 'Sentence to classify sentiment')

st.write(pipe(inp)[0]["label"])
