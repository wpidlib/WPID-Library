from airium import Airium

tree = [
    ["Chassis Class",
        ["HDrive.cpp",
            ["HFunc1", "Func1 Desc"], ["HFunc2", "Func2 Desc"]],
        ["Tank.cpp",
            ["TFunc1", "Func1 Desc"], ["TFunc2", "Func2 Desc"]]],
    ["Mechanism Class",
        ["MFunc1", "Func1 Desc"], ["MFunc2", "Func2 Desc"]],
    ["PID.cpp",
        ["PFunc1", "Func1 Desc"], ["PFunc2", "Func2 Desc"]]
]

def generateCardTree(subList, headNum, head, col, body, accordion):
    with a.div( klass = "card"):
        head = head + "-" + str(headNum)
        with a.div( klass = "card-header", id = head):
            with a.h5( klass = "mb-0"):
                col = col + "-" + str(headNum)
                body = body + "-" + str(headNum)
                with a.a(**{ "class":"collapsed", "role":"button", "data-toggle":"collapse", "href":col, "aria-expanded":"false", "aria-controls":body}):
                    a(subList[0])
        with a.div(**{ "id":body, "class":"collapse",  "data-parent":("#"+accordion), "aria-labelledby":head}):
            with a.div(klass = "card-body"):
                accordion = accordion + "-" + str(headNum)
                with a.div(id = accordion):
                    for x in range(1, len(subList)):
                        print(subList[x])
                        if(len(subList[x])>2):
                            generateCardTree(subList[x], x, head, col, body, accordion)
                        else:

                                generateCard(subList[x], x, head, col, body, accordion)


def generateCard(leaf, headNum, head, col, body, accordion):
    with a.div(klass = "card"):
        head = head + "-" + str(headNum)
        with a.div(klass = "card-header", id = head):
            with a.h5(klass = "mb-0"):
                col = col + "-" + str(headNum)
                body = body + "-" + str(headNum)
                with a.a( **{ "class":"collapsed", "role":"button", "data-toggle":"collapse", "href":col, "aria-expanded":"false", "aria-controls":body}):
                    a(leaf[0])

        with a.div(**{ "id":body, "class":"collapse",  "data-parent":("#"+accordion), "aria-labelledby":head}):
            with a.div(klass = "card-body"):
                a(leaf[1])

a = Airium()

#Outer most parent div
with a.div( id = "accordion"):
    counter = 1
    for item in tree:
        generateCardTree(item, counter, "heading", "#collapse", "collapse", "accordion")
        counter = counter + 1

# Casting the file to a string to extract the value
html = str(a)
# Casting the file to UTF-8 encoded bytes:
html_bytes = bytes(a)
print(html)
