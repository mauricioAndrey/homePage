numero = input("Digite um número para ver sua tabuada: ")
i = 0
print('-'*15)
for i in range(1, 11):
    print('{} x {} = {}'.format(numero, i, int(numero)*int(i)))
print('-'*15)