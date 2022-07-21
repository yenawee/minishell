# minishell


## REQUIREMENTS
- Not interpret unclosed quotes or unspecified special characters like \ or;.
- Not use more than one global variable, think about it and be ready to explain why you do it.
- Show a prompt when waiting for a new command.
- Have a working History.
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- It must implement the builtins:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
- ’ inhibit all interpretation of a sequence of characters.
- " inhibit all interpretation of a sequence of characters except for $.
- Redirections:
  - < should redirect input.
  - \> should redirect output.
  - “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
  - “>>” should redirect output with append mode.
- Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command.
- Environment variables ($ followed by characters) should expand to their values.
- $? should expands to the exit status of the most recently executed foreground
pipeline.
- ctrl-C ctrl-D ctrl-\ should work like in bash.
- When interactive:
  - ctrl-C print a new prompt on a newline.
  - ctrl-D exit the shell.
  - ctrl-\ do nothing.
  
- Anything not asked is not required

## FLOW CHART
<img src="https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F19dfc9a5-b483-4cd2-891d-9773df02b673%2FUntitled.png?table=block&id=417bc390-8dac-49f3-ab14-5c1dff158d76&spaceId=cf1b8bdd-9a75-4920-9590-391452f0ccbd&width=2000&userId=56d57c89-b9e6-45eb-aa02-039b56e56ee7&cache=v2">

## SCREEN SHOT
<img src="https://www.notion.so/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F4860e697-3354-4533-8675-a26c045a3d3c%2FUntitled.png?table=block&id=4a06838b-3432-41a7-8727-cdcd7b73a7a2&spaceId=cf1b8bdd-9a75-4920-9590-391452f0ccbd&width=2000&userId=56d57c89-b9e6-45eb-aa02-039b56e56ee7&cache=v2">


