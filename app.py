import serial
import threading
import datetime
from flask import Flask, render_template, Response
import json

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

last_log = ""

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/attendance')
def get_attendance():
    # ensure_ascii=False 옵션을 써야 한글이 깨지지 않음!
    return Response(
        json.dumps({"students": students, "last_log": last_log}, ensure_ascii=False),
        content_type="application/json; charset=utf-8"
    )

def serial_listen():
    global last_log
    try:
        ser = serial.Serial('COM9', 9600, timeout=1)
        while True:
            line = ser.readline().decode().strip()
            if line:
                print(f"[시리얼 수신] {line}")
                last_log = line
                for s in students:
                    if s["number"] == line:
                        s["time"] = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        print(f"{s['name']} 출석 완료!")
                        break
    except Exception as e:
        print("시리얼 포트 연결 실패:", e)

# 시리얼 수신 스레드 실행
t = threading.Thread(target=serial_listen, daemon=True)
t.start()

if __name__ == "__main__":
    app.run(debug=True)
