import serial
import threading
import datetime
from flask import Flask, render_template, jsonify

app = Flask(__name__)

students = [
    {"number": "30214", "name": "오진규", "time": ""},
    {"number": "30605", "name": "김태민", "time": ""},
    {"number": "30729", "name": "하준영", "time": ""},
    {"number": "31405", "name": "김서영", "time": ""},
    {"number": "30216", "name": "이건영", "time": ""},
    {"number": "31110", "name": "박준호", "time": ""},
    {"number": "30709", "name": "박성현", "time": ""},
    {"number": "31413", "name": "문지훈", "time": ""}
]

@app.route('/attendance')
def get_attendance():
    return jsonify(students)

def serial_listen():
    # 포트명 반드시 환경에 맞게 수정 (예: '/dev/ttyACM0', 'COM3')
    ser = serial.Serial('COM9', 9600)
    while True:
        try:
            line = ser.readline().decode().strip()
            print(f"[시리얼 수신] {line}")
            # 학번 일치 학생 출석 처리
            for s in students:
                if s["number"] == line:
                    s["time"] = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    print(f"{s['name']} 출석 완료!")
                    break
        except Exception as e:
            print("시리얼 에러:", e)

threading.Thread(target=serial_listen, daemon=True).start()

@app.route('/')
def home():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)
