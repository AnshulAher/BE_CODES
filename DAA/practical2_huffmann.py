class Node:
    def __init__(self, ch, freq, left=None, right=None):
        self.ch = ch
        self.freq = freq
        self.left = left
        self.right = right

def build_code_table(root, code, code_table):
    if root is None:
        return
    if root.left is None and root.right is None:
        code_table[root.ch] = code
        return

    build_code_table(root.left, code + '0', code_table)
    build_code_table(root.right, code + '1', code_table)

def main():
    # Take input from the user
    text = input("Enter the text for Huffman encoding: ")

    # Calculate frequency of each character
    freq = {}
    for ch in text:
        freq[ch] = freq.get(ch, 0) + 1

    # Create a priority queue (min-heap) for nodes
    nodes = [Node(ch, frequency) for ch, frequency in freq.items()]
    nodes.sort(key=lambda node: node.freq)

    # Build the Huffman Tree
    while len(nodes) > 1:
        left = nodes.pop(0)
        right = nodes.pop(0)

        sum_freq = left.freq + right.freq
        new_node = Node(None, sum_freq, left, right)
        nodes.append(new_node)
        nodes.sort(key=lambda node: node.freq)

    root = nodes[0]

    # Build the Huffman code table
    huffman_code = {}
    build_code_table(root, "", huffman_code)

    # Display character frequencies
    print("Character frequencies:")
    for ch, frequency in freq.items():
        print(ch, ":", frequency)

    # Display Huffman codes
    print("\nHuffman Codes:")
    for ch, code in huffman_code.items():
        print(ch, ":", code)

if __name__ == "__main__":
    main()
