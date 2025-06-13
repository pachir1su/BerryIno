document.addEventListener("DOMContentLoaded", function () {
  const list = document.getElementById("attendance-list");
  setInterval(async () => {
    const res = await fetch("/attendance");
    const students = await res.json();
    list.innerHTML = "";
    students.forEach((record) => {
      const li = document.createElement("li");
      if (record.time) {
        li.textContent = `${record.number} ${record.name} (${record.time})`;
        li.style.color = "#1558b0";
      } else {
        li.textContent = `${record.number} ${record.name} (미출석)`;
        li.style.color = "#aaa";
      }
      list.appendChild(li);
    });
  }, 2000);
});
