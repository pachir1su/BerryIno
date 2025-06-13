const LATE_TIME = "09:00:00";
function isLate(timeStr) {
  if (!timeStr) return false;
  const t = timeStr.split(" ")[1]; // "YYYY-MM-DD HH:MM:SS" -> "HH:MM:SS"
  return t > LATE_TIME;
}

document.addEventListener("DOMContentLoaded", function () {
  const list = document.getElementById("attendance-list");
  const logBox = document.getElementById("log-box");
  let prevLog = "";
  setInterval(async () => {
    const res = await fetch("/attendance");
    const data = await res.json();
    const students = data.students || data;
    list.innerHTML = "";
    students.forEach((record) => {
      const li = document.createElement("li");
      if (record.time) {
        if (isLate(record.time)) {
          li.innerHTML = `<b style="color:red">${record.number} ${record.name} (${record.time}) - 지각</b>`;
        } else {
          li.innerHTML = `<span style="color:#1558b0">${record.number} ${record.name} (${record.time})</span>`;
        }
      } else {
        li.innerHTML = `<span style="color:#aaa">${record.number} ${record.name} (미출석)</span>`;
      }
      list.appendChild(li);
    });
    // 로그 표시
    if (data.last_log && data.last_log !== prevLog) {
      logBox.innerText = `[학번 수신] ${data.last_log}`;
      prevLog = data.last_log;
    }
  }, 2000);
});
