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
            <ul>
                <li><a href="#projects">Projects</a></li>
                <li><a href="#contact">Contact</a></li>
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