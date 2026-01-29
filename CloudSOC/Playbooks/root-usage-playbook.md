# Root User Activity Playbook

## 1. Alert Overview
- **Severity:** Critical
- **Category:** Exploitation
- **Data Source:** AWS CloudTrail
- **Trigger Condition:** Root account usage has been detected

## 2. Why This Alert Matters
Root account usage could indicate the highest level of compromise and potential damage.

## 3. Initial Triage (First 5 Minutes)
- Identify any related alerts (IAM Escalation, Login Attempts)
- Confirm source IP address and region
- Determine whether the usage is scheduled (i.e. billing) or unscheduled
- Check what actions have been taken by the user

## 4. Investigation Steps
### Review the triggering event
```sql
fields @timestamp, eventName, errorCode, userIdentity.userName, sourceIPAddress, userAgent
| filter eventName="identityType = Root"
| sort @timestamp desc
```
## 5. False Positive Analysis

Possible benign causes:
- scheduled usage
- Accidental login by trusted user

Validate:
- confirm unscheduled usage
- Check any correlating alerts
- Review Actions taken

## 6. Containment Actions
- Change Root Password
- Delete any Associated Keys
- Rotate/enable MFA
- Revoke any changes made by checking CloudTrail logs

## 7. Eradication & Recovery
- Secure root email
- Use IAM roles for management purposes
- Force password reset if suspected compromise

## 8. Post-Incident Improvements
- use two person rule, no one has root password and mfa at one time
- Set up SNS notifications if not on for alarms
