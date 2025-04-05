class Swag:
    def __init__(self, swagmemory_size=30000):
        self.swagmemory = bytearray(swagmemory_size)
        self.pointerggggg = 0
    def executeStuff(self, code):
        gregloop = []
        code_length = len(code)
        i = 0
        while i < code_length:
            instruction = code[i]
            if instruction == '>':
                self.pointerggggg += 1
                if self.pointerggggg >= len(self.swagmemory):
                    self.swagmemory.extend(bytearray(len(self.swagmemory)))
            elif instruction == '<':
                if self.pointerggggg > 0:
                    self.pointerggggg -= 1
                else:
                    print("error: pointer out of bounds")
                    return
            elif instruction == '+':
                self.swagmemory[self.pointerggggg] = (self.swagmemory[self.pointerggggg] + 1) % 256
            elif instruction == '-':
                self.swagmemory[self.pointerggggg] = (self.swagmemory[self.pointerggggg] - 1) % 256
            elif instruction == '.':
                print(chr(self.swagmemory[self.pointerggggg]), end='')
            elif instruction == ',':
                try:
                    user_input = input()
                    if user_input:
                        self.swagmemory[self.pointerggggg] = ord(user_input[0])
                    else:
                        self.swagmemory[self.pointerggggg] = 0
                except EOFError:
                    self.swagmemory[self.pointerggggg] = 0
            elif instruction == '[':
                if self.swagmemory[self.pointerggggg] == 0:
                    nestL = 1
                    while nestL > 0 and i < code_length - 1:
                        i += 1
                        if code[i] == '[':
                            nestL += 1
                        elif code[i] == ']':
                            nestL -= 1
                    if nestL > 0:
                        print("error: unmatched '['")
                        return
                else:
                    gregloop.append(i)
            elif instruction == ']':
                if not gregloop:
                    print("error: unmatched ']'")
                    return
                if self.swagmemory[self.pointerggggg] != 0:
                    i = gregloop[-1]
                else:
                    gregloop.pop()
            i += 1
        if gregloop:
            print("error: unmatched '['")
    def bracketgreg(self, code):
        bracketthing = []
        for i, char in enumerate(code):
            if char == '[':
                bracketthing.append(i)
            elif char == ']':
                if not bracketthing:
                    print(f"error: unmatched ']' at position {i}")
                    return False
                bracketthing.pop()
        if bracketthing:
            print(f"error: unmatched '[' at position {bracketthing[-1]}")
            return False
        return True
    def fileexxxxxxxxx(self, filename):
        try:
            with open(filename, 'r') as file:
                code = ''.join(c for c in file.read() if c in '><+-.,[]')
            if self.bracketgreg(code):
                self.executeStuff(code)
        except FileNotFoundError:
            print(f"error: could not open file {filename}")
if __name__ == "__main__":
    import sys
    interpreter = Swag()
    if len(sys.argv) > 1:
        interpreter.fileexxxxxxxxx(sys.argv[1])
    else:
        print("enter brainfucm coddde (type 'end' to stop):")
        code = ""
        while True:
            line = input()
            if line.lower() == "end":
                break
            code += ''.join(c for c in line if c in '><+-.,[]')
        print("\nrunning")
        if interpreter.bracketgreg(code):
            print("=" * 60)
            interpreter.executeStuff(code)
    print("\npress enter to exit...")
    input()
