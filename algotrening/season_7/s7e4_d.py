n = int(input())
apps = []
output = []

for _ in range(n):
    command = input().strip()
    if command.startswith('Run'):
        name = command[4:].strip()
        apps.insert(0, name)
    else:
        k = command.count('+Tab')
        
        pos = k % len(apps)
        selected = apps.pop(pos)
        apps.insert(0, selected)

    output.append(apps[0])

print('\n'.join(output))