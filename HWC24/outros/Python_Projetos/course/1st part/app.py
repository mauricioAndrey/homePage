# outputs ++++++++++++++++++++++++++++++++++++++++++++++++
print('Joshua\n')
print("o----")
print(" ||||")

# comentário ++++++++++++++++++++++++++++++++++++++++++++++++
print('*' * 10) # multiplicação de string

#variáveis ++++++++++++++++++++++++++++++++++++++++++++++++
price = 10 #integer
rating = 2.4 #float
name = 'Joshua' #string
is_published = False #boolean
print(price, rating, name, is_published)

#challenge ----------------------------------------------
name = "John Smith"
age = "20"
is_new = True

name2 = input("What is your name? ")
age2 = input("What is your age? ")
is_new2 = input("Are you new here? ")

if name2 == name and age2 == age:
    print("You are " + name + " and you are " + age + " years old.")
else:
    print("You are not John Smith. " + "You are " + name2 + " and you are " + age2 + " years old.")

# inputs ++++++++++++++++++++++++++++++++++++++++++++++++
input("What is your name? ") #mensagem que espera uma resposta
thing = input("something: ") #salvando o input em uma variável

#convertendo inputs ++++++++++++++++++++++++++++++++++++++++++++++++
birth_year = input("Birth year: ")
print(type(birth_year)) #verificando o tipo da variável
age = 2025 - int(birth_year) #convertendo string para integer
print(type(age))
print(age)

#parei no momento 28:00
