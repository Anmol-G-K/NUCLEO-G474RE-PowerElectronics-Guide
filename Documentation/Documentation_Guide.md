# SPARK Project Documentation Guide

This directory contains the official templates and guidelines for writing project documentation in the **SPARK** repository. 

To maintain consistency across all projects (Projects 01 to 06 and future additions), we write our detailed documentation in **LaTeX** using a standardized article template.

---

## 📁 Directory Contents

- **[template.tex](./template.tex)**: The master LaTeX template file containing layout configurations, style definitions, custom macros, TikZ diagrams, and inline instructions.
- **[template.pdf](./template.pdf)**: The pre-compiled reference version of the template showing how the output should look.
- **`embedded_workflow.png`**: The default embedded workflow diagram used in the template's overview section.

---

## 🚀 Quick Start: How to Use the Template

1. **Duplicate the Template:** 
   Copy the `template.tex` file to your new project's subfolder and rename it:
   `NN_ProjectName.tex` (where `NN` is the two-digit project number, e.g., `07_Phase_Shifted_PWM.tex`).
2. **Configure Custom Metadata:**
   Open the file and update the metadata variables under the `CUSTOM COMMANDS` section:
   ```latex
   \newcommand{\projecttitle}{Your Project Title}
   \newcommand{\projectnumber}{NN}
   \newcommand{\projectdescription}{One-sentence description.}
   ```
3. **Select Your Framework:**
   Choose the appropriate sections of the template that match your project:
   - Keep the **STM32CubeIDE** section if you have a manual C firmware path.
   - Keep the **MATLAB Embedded Coder** section if you use Simulink/model-based design.
   - Delete any unused framework sections and update the framework subtitle line on the title page.
4. **Replace Guidance Text:**
   Replace all italicized `\textit{[Guidance: ...]}` text blocks throughout the document with your actual project details, descriptions, tables, and code snippets.

---

## 📊 Diagram & Sketching Tools

When designing system architectures, block diagrams, or electrical wiring schematics, we recommend using the following tools:

- **Excalidraw:** Excellent for clean, hand-drawn-style sketches.
  - **Web:** [excalidraw.com](https://excalidraw.com/)
  - **VS Code / VSCodium:** Search for the **Excalidraw** extension in the marketplace to edit `.excalidraw` or `.excalidraw.png` files directly inside your editor.
- **Draw.io (diagrams.net):** Great for structured technical flowcharts, block diagrams, and grid-based schematics.
  - **Web:** [app.diagrams.net](https://app.diagrams.net/)
  - **VS Code:** Search for the **Draw.io Integration** extension.

---

## 🛠️ How to Compile LaTeX Documents

You can compile your `.tex` document into a PDF using either a local LaTeX distribution or web-based editors.

### Option A: Web-Based (Recommended & Zero-Setup)
- **Overleaf:** A free, web-based collaborative LaTeX editor that handles all packages and compilers in the cloud.
  1. Go to [Overleaf](https://www.overleaf.com/).
  2. Create a new project and upload `template.tex` along with any required images (like `embedded_workflow.png`).
  3. Click **Recompile** (ensure the compiler is set to PDFLaTeX, which is default).

### Option B: Local Compilation
To compile locally on your machine, you will need a LaTeX distribution and compiler:
1. **Install a LaTeX Distribution:**
   - **Windows:** [MiKTeX](https://miktex.org/)
   - **macOS:** [MacTeX](https://www.tug.org/mactex/)
   - **Linux:** [TeX Live](https://www.tug.org/texlive/)
2. **Compile twice** using your editor's build button, or run the following command in your terminal (running it twice ensures table of contents and internal references resolve correctly):
   ```bash
   pdflatex NN_ProjectName.tex
   pdflatex NN_ProjectName.tex
   ```

---

## 📌 Document Conventions to Keep in Mind

- **Image Paths:** Store all project images within their respective subfolders (e.g., `NN_ProjectName/CUBE_IDE/imagename.png`) and reference them using:
  `\includegraphics[width=0.85\textwidth]{NN_ProjectName/sub/name.png}`
- **Caption Rule:** Keep figure and table captions to **45 words or fewer**. Briefly describe the item, its role, and one non-obvious detail not immediately visible to the reader.
- **Code Listings:** Place your code snippets inside `\begin{lstlisting}[language=C] ... \end{lstlisting}` blocks for proper syntax highlighting.
