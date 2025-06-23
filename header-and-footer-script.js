document.addEventListener("DOMContentLoaded", function() {
    document.getElementById('header').innerHTML = headerHTML();
});

document.addEventListener("DOMContentLoaded", function() {
    document.getElementById('footer').innerHTML = footerHTML();
});

function headerHTML() {
    let header = `
        <nav>
            <h1>Welcome to My CS499 ePortfolio</h1>
            <ul class="nav-menu">
                <li><a href="index.html#about">Home</a></li>
                <li class="dropdown">
                    <a href="#">Enhancements ▼</a>
                    <ul class="dropdown-content">
                        <li><a href="enhancement-one.html">Enhancement One</a></li>
                        <li><a href="enhancement-two.html">Enhancement Two</a></li>
                        <li><a href="enhancement-three.html">Enhancement Three</a></li>
                    </ul>
                </li>
                <li><a href="index.html#contact">Contact</a></li>
            </ul>
        </nav>
    `;
    return header;
}

function footerHTML() {
    let footer = `
        <p>&copy; 2025 Scott Enos. All rights reserved.</p>
        `;

        return footer;
}