# Small Language Model (SLM)
This program acts as a very basic language model. After receiving a training text as input, the model generates original text based on the frequencies of k-grams in the text (sequences of `k` characters).

## Build

Compile using `make`. A C++17-compatible compiler is required.

```bash
make
```

To remove generated object files and the slm executable:

```bash
make clean
```

## Usage instructions

```text
./slm [-a alpha] k file length
```

Examples:

```bash
./slm 2 test.txt 100
./slm -a 0.5 3 test.txt 200
```

### Arguments

- `k`: Size of each k-gram. It needs to be a positive integer.
- `alpha`: Pseudocount used to smooth the probability distribution. Optional; when not used it defaults to `0`.
- `file`: Filename of the input training text.
- `length`: Desired output length in characters. It needs to be a positive of at least `k`

## How the program works

### 1. Building the Model

The program reads the input training text and performs calculations:

- **K-gram frequencies:** A window of size `k` moves through the whole text, counting how often each k-gram occurs.
- **Character transitions:** For each k-gram, the program counts which and how many times some character follow it.
- **Alphabet:** The whole set of distinct characters that appear in the training text.

### 2. Generating Text

1. The generator chooses an initial k-gram, weighted by its frequency in the training text.
2. Calculate the probability distribution for the next character considering the current k-gram.
3. the next character is selected according to the distribution.
4. Append the character to the output and update the current k-gram by keeping the last `k` characters.
5. Everything is repeated until the output length is reached or generation stops.

### 3. Pseudocounts

The parameter `alpha` smooths the transition probabilities. It's added to the count of every character in the alphabet when calculating the probability for the next character.

For a k-gram `w` and a possible next character `c`, the probability is:

\[
P(c \mid w) = \frac{n(w,c)+\alpha}{n(w)+\alpha|\Sigma|}
\]

where:

- \(n(w,c)\) is the number of times character `c` follows k-gram `w`.
- \(n(w)\) is the total number of observed transitions following `w`.
- \(|\Sigma|\) is the number of distinct characters in the alphabet.
- \(\alpha\) is the pseudocount.

If `alpha` is greater than zero, unseen transitions have nonzero probabilities. If a k-gram has no observed following characters, the distribution becomes uniform over the alphabet.

When `alpha` is zero, the model uses the observed transition frequencies without smoothing. If generation reaches a k-gram with no observed continuation, it stops early.
