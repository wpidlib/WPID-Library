from airium import Airium

tree = [
    ["Chassis Class",
        ["HDrive.cpp",
            ["HDrive(float track_width, float wheel_radius, float center_wheel_radius, vex::motor_group* left, vex::motor_group* right, vex::motor_group* center)", "Func1 Desc"],
            ["setStraightPID(PID pid)", "Func2 Desc"],
            ["setTurnPID(PID pid)", "Func3 Desc"],
            ["setStrafePID(PID pid)", "Func4 Desc"],
            ["spin(int left_velocity, int right_velocity, int center_velocity)", "Func5 Desc"],
            ["spin(int sides, int center)", "Func6 Desc"],
            ["resetEncoders()", "Func7 Desc"],
            ["straight(float distance, int max_speed)", "Func8 Desc"],
            ["turn(int target_angle, int max_speed)", "Func9 Desc"],
            ["strafe(float distance, int max_speed)", "Func10 Desc"],
            ["diagonal(float straight_distance, float strafe_distance, int straight_max_speed)", "Func11 Desc"],
            ["setTarget(float left_target, float right_target, float center_target, int l_max_spd, int r_max_spd, int c_max_spd, PID pid)", "Func12 Desc"],
            ["leftEncoder(rotationUnits units)", "Func13 Desc"],
            ["rightEncoder(rotationUnits units)", "Func14 Desc"],
            ["centerEncoder(rotationUnits units)", "Func15 Desc"],
            ["setEncoders(encoder* left, encoder* right, encoder* center)", "Func16 Desc"],
            ["setBrakeType(brakeType type)", "Func17 Desc"],
            ["setOffset(float straight, float turn, float center)", "Func18 Desc"],
            ["stop()", "Func19 Desc"],
            ["setMaxAcceleration(float max_accel)", "Func20 Desc"],
            ["setName(char* name)", "Func21 Desc"]],
        ["Tank.cpp",
            ["Tank(float track_width, float wheel_radius, vex::motor_group* left, vex::motor_group* right)", "Func1 Desc"],
            ["setStraightPID(PID pid)", "Func2 Desc"],
            ["setTurnPID(PID pid)", "Func3 Desc"],
            ["spin(int left_velocity, int right_velocity)", "Func5 Desc"],
            ["spin(int sides)", "Func6 Desc"],
            ["resetEncoders()", "Func7 Desc"],
            ["straight(float distance, int max_speed)", "Func8 Desc"],
            ["turn(int target_angle, int max_speed)", "Func9 Desc"],
            ["strafe(float distance, int max_speed)", "Func10 Desc"],
            ["diagonal(float straight_distance, float strafe_distance, int straight_max_speed)", "Func11 Desc"],
            ["setTarget(float left_target, float right_target, int l_max_spd, int r_max_spd, PID pid)", "Func12 Desc"],
            ["leftEncoder(rotationUnits units)", "Func13 Desc"],
            ["rightEncoder(rotationUnits units)", "Func14 Desc"],
            ["setEncoders(encoder* left, encoder* right)", "Func16 Desc"],
            ["setBrakeType(brakeType type)", "Func17 Desc"],
            ["setOffset(float straight, float turn)", "Func18 Desc"],
            ["stop()", "Func19 Desc"],
            ["setMaxAcceleration(float max_accel)", "Func20 Desc"],
            ["setName(char* name)", "Func21 Desc"]]],
    ["Mechanism Class",
        ["Mechanism(motor_group* motors, float gear_ratio)", "Func1 Desc"],
        ["spin(int velocity)", "Func1 Desc"],
        ["stop()", "Func1 Desc"],
        ["setPosition(float angle, float max_speed)", "Func1 Desc"],
        ["getPosition(rotationUnits units)", "Func1 Desc"],
        ["resetPosition()", "Func1 Desc"],
        ["setBrakeType(brakeType type)", "Func1 Desc"],
        ["setPID(PID pid)", "Func2 Desc"],
        ["setOffset(float offset)", "Func1 Desc"],
        ["setMaxAcceleration(float max_accel)", "Func1 Desc"],
        ["setBounds(float upper_bound, float lower_bound)", "Func1 Desc"],
        ["setTimeout(int timeout)", "Func1 Desc"],
        ["setName(char* name)", "Func1 Desc"]],
    ["PID.cpp",
        ["calculateSpeed(float error, float max_speed)", "Func1 Desc"],
        ["setErrorRange(float bound)", "Func1 Desc"],
        ["cont(float error)", "Func1 Desc"],
        ["reset(void)", "Func1 Desc"],
        ["logCSV(float error, float speed, float proportional, float integral, float derivative)", "Func1 Desc"],
        ["copy()", "Func2 Desc"]],
    ["Conversion.cpp",
        ["standardize(float value, measurement value_type)", "Func1 Desc"],
        ["convertTo(float value, measurement output_type)", "Func2 Desc"]]
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
                        if(type(subList[x][1]) is list):
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
#html_bytes = bytes(a)

print(html)
