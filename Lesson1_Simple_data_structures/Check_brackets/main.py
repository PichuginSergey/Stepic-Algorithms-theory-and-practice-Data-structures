# Check brackets in message
def check_brackets(msg):
    stack = []
    for idx in range(len(msg)):
        elm = msg[idx]
        if (elm in ('(', '{', '[')):
            stack.append((elm, idx+1))
        elif (elm in (')', '}', ']')):
            if len(stack) == 0:
                print idx+1
                return
            if (elm == ')' and stack[-1][0] == '(') or \
               (elm == '}' and stack[-1][0] == '{') or \
               (elm == ']' and stack[-1][0] == '['):
                stack.pop()
            else:
                print idx+1
                return
    if len(stack) == 0:
        print 'Success'
    else:
        print stack[-1][1]

msg = input()
check_brackets(msg)