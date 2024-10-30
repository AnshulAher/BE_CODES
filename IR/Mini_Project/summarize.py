import tkinter as tk
from tkinter import filedialog, messagebox
import nltk
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
from collections import defaultdict
import os

# Download NLTK resources
nltk.download('punkt', quiet=True)
nltk.download('stopwords', quiet=True)


# Summarization functions
def preprocess_text(text):
    return text.lower()


def build_similarity_matrix(sentences):
    similarity_matrix = {}
    for i, sentence1 in enumerate(sentences):
        similarity_matrix[i] = {}
        for j, sentence2 in enumerate(sentences):
            if i != j:
                similarity = cosine_similarity(sentence1, sentence2)
                if similarity > 0:
                    similarity_matrix[i][j] = similarity
    return similarity_matrix


def cosine_similarity(sentence1, sentence2):
    stop_words = set(stopwords.words('english'))
    words1 = [word.lower() for word in word_tokenize(sentence1) if word.isalnum() and word.lower() not in stop_words]
    words2 = [word.lower() for word in word_tokenize(sentence2) if word.isalnum() and word.lower() not in stop_words]

    unique_words = set(words1 + words2)
    vec1 = [words1.count(word) for word in unique_words]
    vec2 = [words2.count(word) for word in unique_words]

    dot_product = sum(a * b for a, b in zip(vec1, vec2))
    magnitude1 = sum(a ** 2 for a in vec1) ** 0.5
    magnitude2 = sum(b ** 2 for b in vec2) ** 0.5

    if not magnitude1 or not magnitude2:
        return 0.0

    return dot_product / (magnitude1 * magnitude2)


def score_sentences(text):
    sentences = sent_tokenize(text)
    sentence_scores = defaultdict(float)

    words = word_tokenize(text.lower())
    freq = nltk.FreqDist(words)

    for i, sentence in enumerate(sentences):
        for word in word_tokenize(sentence.lower()):
            if word in freq:
                sentence_scores[i] += freq[word]

    return sentence_scores


def summarize_text(text):
    text = preprocess_text(text)
    sentence_scores = score_sentences(text)
    threshold = sum(sentence_scores.values()) / len(sentence_scores)

    selected_sentences = [sent for i, sent in enumerate(sent_tokenize(text)) if sentence_scores[i] >= threshold]

    return ' '.join(selected_sentences)


# GUI Application
def browse_input_file():
    input_file_path.set(filedialog.askopenfilename(filetypes=[("Text Files", "*.txt")]))


def browse_output_file():
    output_file_path.set(filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text Files", "*.txt")]))


def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()


def write_file(file_path, content):
    with open(file_path, 'w') as file:
        file.write(content)


def summarize_file():
    input_file = input_file_path.get()
    output_file = output_file_path.get()

    if not input_file or not output_file:
        messagebox.showerror("Error", "Please select both input and output files.")
        return

    try:
        content = read_file(input_file)
        summary = summarize_text(content)
        write_file(output_file, summary)

        messagebox.showinfo("Success", "Text has been summarized and saved.")
        os.startfile(output_file)  # Open the output file

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred: {e}")


# Setup Tkinter GUI
root = tk.Tk()
root.title("Text Summarizer")

input_file_path = tk.StringVar()
output_file_path = tk.StringVar()

tk.Label(root, text="Input File:").grid(row=0, column=0, padx=10, pady=10)
tk.Entry(root, textvariable=input_file_path, width=40).grid(row=0, column=1, padx=10, pady=10)
tk.Button(root, text="Browse", command=browse_input_file).grid(row=0, column=2, padx=10, pady=10)

tk.Label(root, text="Output File:").grid(row=1, column=0, padx=10, pady=10)
tk.Entry(root, textvariable=output_file_path, width=40).grid(row=1, column=1, padx=10, pady=10)
tk.Button(root, text="Browse", command=browse_output_file).grid(row=1, column=2, padx=10, pady=10)

tk.Button(root, text="Submit", command=summarize_file).grid(row=2, column=1, padx=10, pady=20)

root.mainloop()
