import re

# TODO: UVa outputs RTE.

TOKENS = [
    # Regex, (type, opening)
    (re.compile(r'\(\*'), ('par_star', True)),
    (re.compile(r'\*\)'), ('par_star', False)),
    (re.compile(r'\('), ('par', True)),
    (re.compile(r'\)'), ('par', False)),
    (re.compile(r'\{'), ('brace', True)),
    (re.compile(r'\}'), ('brace', False)),
    (re.compile(r'\['), ('bracket', True)),
    (re.compile(r'\]'), ('bracket', False)),
    (re.compile(r'\<'), ('angle', True)),
    (re.compile(r'\>'), ('angle', False)),
    (re.compile(r'.'), ('other', False)),
]

def lexer(input_text):
    tokens = []
    pos = 0

    while pos < len(input_text):
        match = None
        for pattern, token_classification in TOKENS:
            if match := pattern.match(input_text, pos):
                tokens.append(token_classification)
                pos = match.end()
                break
        if not match:
            pos += 1

    return tokens

def matching_brackets(tokens):
    stack = []
    for i, (token_type, opening) in enumerate(tokens, 1):
        if token_type == 'other':
            continue

        if opening:
            stack.append((token_type, opening))
        else:
            other_token_type, other_opening = stack.pop()
            if token_type != other_token_type:
                return i
    return -1

def main():
    try:
        while True:
            text = input()
            tokens = lexer(text)
            unmatching_position = matching_brackets(tokens)
            if unmatching_position == -1:
                print('YES')
            else:
                print('NO', unmatching_position)
    except EOFError:
        return

if __name__ == '__main__':
    main()
