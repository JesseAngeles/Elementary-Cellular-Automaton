document.addEventListener("DOMContentLoaded", function () {
    document.querySelectorAll('a[href^="#img"]').forEach(link => {
        link.addEventListener("click", function (e) {
            e.preventDefault();
            let targetId = this.getAttribute("href").substring(1);
            let targetElement = document.getElementById(targetId);

            if (targetElement) {
                let rect = targetElement.getBoundingClientRect();
                let isVisible = rect.top >= 0 && rect.bottom <= window.innerHeight;

                if (!isVisible) {
                    targetElement.scrollIntoView({ behavior: "smooth", block: "center" });
                }

                targetElement.classList.add("resaltar");
                setTimeout(() => {
                    targetElement.classList.remove("resaltar");
                }, 1500);
            }
        });
    });
});
